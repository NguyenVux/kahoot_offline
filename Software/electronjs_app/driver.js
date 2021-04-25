const SerialPort = require('serialport')
const load_setting = require('./util.js').load_setting
const Delimiter = require('@serialport/parser-delimiter')
const config = load_setting("driver_config.json")

if(config === undefined) 
    process.exit(-1)

const port = SerialPort(config.port,{baudRate: config.baudRate})
const ESP32_parser = port.pipe(new Delimiter({ delimiter: config.delimiter }))



module.exports = parser