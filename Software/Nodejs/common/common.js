const {load_setting} = require('./setting_loader')

function isArrayOfType(arr, type) {
    return Array.isArray(arr) && arr.filter(i => typeof i === type).length === arr.length;
}
module.exports = {
    load_setting: load_setting,
    isArrayOfType: isArrayOfType
}