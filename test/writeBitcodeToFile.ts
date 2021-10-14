import path from 'path';
import fs from 'fs';
import { WriteBitcodeToFile } from '..';
import getAddModule from './add';

export default function (): void {
    const module = getAddModule(false);
    if (module) {
        const dir = path.join(__dirname, 'temp');
        const filepath = path.join(dir, 'add.out.bc');
        if (!fs.existsSync(dir)) {
            fs.mkdirSync(dir);
        }
        if (fs.existsSync(filepath)) {
            fs.unlinkSync(filepath);
        }
        WriteBitcodeToFile(module, filepath);
        console.log(`Bitcode was successfully written to the ${filepath}`);
    }
}
