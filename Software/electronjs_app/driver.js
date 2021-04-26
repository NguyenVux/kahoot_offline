const SerialPort = require('serialport')
const Delimiter = require('@serialport/parser-delimiter')

const Event = require('events')
const { count } = require('console')
const config = require("./util").load_setting("driver_config.json")





if (config === undefined)
    process.exit(-1)
const port = SerialPort(config.port, { baudRate: config.baudRate })
const parser = port.pipe(new Delimiter({ delimiter: config.delimiter }))


function logBase2(bits)
{
    let count = 0;
    while(bits)
    {
        bits >>=1;
        count++;
    }
    return count;
}
function data_parser(data) {
    {
        const buffer_size = 7
        if (!Buffer.isBuffer(data)) throw `Expected buffer type\nbut recieved ${typeof(data)}`;

        if (data.length != buffer_size) 
        {
            console.log(data)
            throw `\nExpected buffer size: ${buffer_size}B\nrecieve: ${data.length}B`;
        }
    }
    let data_object={};
    data_object[`${data[0]}:${data[1]}:${data[2]}:${data[3]}:${data[4]}:${data[5]}`] = logBase2(data[6]);
    return data_object
}



dataEvent = new Event()
parser.on("data", (data) => {
    dataEvent.emit("data", data_parser(data))
})

module.exports = dataEvent