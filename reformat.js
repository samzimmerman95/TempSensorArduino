import data from './lake-test-export.json' assert { type: 'json' };
import * as fs from 'fs';

var newData = {};

for (const [key, value] of Object.entries(data)) {
    if (Number(key) > 1661475600) {
        newData[key] = [value[2], value[4], value[1], value[3], value[0]];
    }
}
// console.log(newData);

const formatted = JSON.stringify(newData, null, 2);

// write JSON string to a file
fs.writeFile('only-lake.json', formatted, (err) => {
    if (err) {
        throw err;
    }
    console.log("JSON data is saved.");
});