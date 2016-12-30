require(`./tools`);

let fs = require(`fs`);
let vm = require(`vm`);

let testFiles = process.argv.slice(2).map(file => {
    return fs.readFileSync(file).toString();
});

let testResults = new Map();

for (let type of [ `node`, `browser` ]) {

    for (let file of testFiles) {

        vm.runInNewContext(file, Object.assign(Object.create(global), {

            Yoga: require(`../sources/entry-${type}`),

            YGBENCHMARK: function (name, fn) {

                let testEntry = testResults.get(name);

                if (testEntry === undefined)
                    testResults.set(name, testEntry = new Map());

                let start = Date.now();
                fn();
                let end = Date.now();

                testEntry.set(type, end - start);

            }

        }));

    }

}

console.log(`Note: those tests are independants; there is no time relation to be expected between them`);

for (let [ name, results ] of testResults) {

    console.log();

    let min = Math.min(Infinity, ... results.values());

    console.log(name);

    for (let [ type, result ] of results) {
        console.log(`  - ${type}: ${result}ms (${Math.round(result / min * 10000) / 100}%)`);
    }

}
