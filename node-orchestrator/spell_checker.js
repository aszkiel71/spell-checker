const { spawn } = require('child_process');

class SpellChecker {
    constructor() {
        this.daemonProcess = null;
        this.ready = false;
        this.pythonScriptPath = '../python-service/spell_corrector.py';
    }

    async ensureDaemon() {
        if (!this.ready) {
            await this.initDaemon();
            this.ready = true;
        }
    }

    async initDaemon() {


        this.daemonProcess = spawn('../cpp-service/trie_service.exe', ['--daemon']);

        return new Promise(resolve => {
            this.daemonProcess.stderr.on('data', (data) => {
                if (data.toString().includes('ready for commands')) {
                    resolve();
                }
            });
        });
    }

    async callCppTrie(command, word) {
        await this.ensureDaemon();

        return new Promise((resolve) => {
            // send command to daemon
            this.daemonProcess.stdin.write(`${command} ${word}\n`);

            // reading response
            const onData = (data) => {
                this.daemonProcess.stdout.removeListener('data', onData);
                resolve(data.toString().trim());
            };

            this.daemonProcess.stdout.once('data', onData);
        });
    }

    async callPythonCorrector(wrongWord, dictWords) {
        return new Promise((resolve, reject) => {
            const firstWords = dictWords.split(',').slice(0, 1000).join(',');

            const process = spawn('python', [this.pythonScriptPath, wrongWord, firstWords]);

            let output = '';

            process.stdout.on('data', (data) => {
                output += data.toString();
            });

            process.on('close', (code) => {
                const result = output.trim();

                if (code === 0 && result && result !== 'None') {
                    resolve(result);
                } else {
                    resolve(wrongWord);
                }
            });

            process.on('error', (error) => {
                resolve(wrongWord);
            });
        });
    }

    async checkSingleWord(word) {
    try {
        // Case handling
        const wasCapitalized = word[0] === word[0].toUpperCase();
        const lowerWord = word.toLowerCase();



        const exists = await this.callCppTrie('search', lowerWord);


        if (exists === 'true') {
            return word; // Return original case
        }

        let prefix;
        if (lowerWord.length >= 6) {
            prefix = lowerWord.substring(0, 3);
        } else if (lowerWord.length > 4) {
            prefix = lowerWord.substring(0, 2);
        } else {
            prefix = lowerWord.substring(0, 1);
        }


        const allWords = await this.callCppTrie('autocomplete', prefix);

        const corrected = await this.callPythonCorrector(lowerWord, allWords);

        // Restore case
        if (wasCapitalized && corrected && corrected.length > 0) {
            const result = corrected[0].toUpperCase() + corrected.slice(1);
            return result;
        } else {
            return corrected;
        }

    } catch (error) {

        return word;
    }
}

    async correctSentence(sentence) {
        const words = sentence.split(' ');
        const correctedWords = [];

        for (const word of words) {
            if (word.trim() === '') {
                continue;
            }

            const correctedWord = await this.checkSingleWord(word.trim());
            correctedWords.push(correctedWord);
        }

        return correctedWords.join(' ');
    }

    shutdown() {
        if (this.daemonProcess) {
            this.daemonProcess.stdin.write('exit\n');
        }
    }
}

module.exports = SpellChecker;
