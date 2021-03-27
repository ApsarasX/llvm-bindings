const path = require('path');
const fs = require('fs');
const {WriteBitcodeToFile} = require('..');
const getAddModule = require('./add');

module.exports = function () {
    const module = getAddModule(false);
    if (module) {
        const dir = path.join(__dirname, "temp");
        const filepath = path.join(dir, "add.out.bc");
        if (!fs.existsSync(dir)) {
            fs.mkdirSync(dir);
        }
        if (fs.existsSync(filepath)) {
            fs.unlinkSync(filepath);
        }
        WriteBitcodeToFile(module, filepath);
        console.log(`Bitcode was successfully written to the \`${filepath}\``);
    }
}