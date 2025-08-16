const SpellChecker = require('./spell_checker');
const fs = require('fs');

async function main() {
    if (process.argv.length < 3) {
        console.log('Usage: node sc.js "text" OR node index.js file.txt');
        console.log('Examples:');
        console.log('  node sc.js "polska kontytucja"');
        console.log('  node sc.js input.txt > output.txt');
        process.exit(1);
    }

    let inputText;
    const input = process.argv[2];


if (input.endsWith('.txt')) {
    try {
        inputText = fs.readFileSync(input, 'utf8');
        inputText = inputText
        .replace(/\r\n/g, '\n')
        .replace(/\0/g, '')
        .trim();
        console.error(`Processing file: ${input}`);
    } catch (error) {
        console.error(`Error reading file: ${error.message}`);
        process.exit(1);
    }
    } else {
        inputText = input;
    }

    const checker = new SpellChecker();


    const corrected = await checker.correctSentence(inputText.trim());
    console.log(corrected);
    checker.shutdown();
    process.exit(0);
}

main().catch(error => {
    console.error('Error:', error.message);
    process.exit(1);
});
