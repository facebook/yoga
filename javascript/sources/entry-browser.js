var nbind = null;

try {

    nbind = require('../build/Release/nbind.js');

} catch (err) {

    try {
        nbind = require('../build/Debug/nbind.js');
    } catch (err2) {
        throw err;
    }

}

var ran = false;
var ret = null;

nbind({}, function (err, result) {

    if (ran)
        return;

    ran = true;

    if (err)
        throw err;

    ret = result;

});

if (!ran)
    throw new Error('Failed to load the yoga module - it needed to be loaded synchronously, but didn\'t');

module.exports = require('./entry-common')(ret.bind, ret.lib);
