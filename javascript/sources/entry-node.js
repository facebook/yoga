var nbind = require('nbind');
var ret = nbind.init(__dirname + '/../');

module.exports = require('./entry-common')(ret.bind, ret.lib);
