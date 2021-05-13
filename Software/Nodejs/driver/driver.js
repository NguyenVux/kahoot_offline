const SerialPort = require('serialport')
const Delimiter = require('@serialport/parser-delimiter')
const Event = require('events')
const {join: join_path} = require('path')
const {load_setting } = require('../common')


const port = SerialPort("config.port", { baudRate: 115200 })
const parser = port.pipe(new Delimiter({ delimiter: "config.delimiter" }))


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

class Driver{
    constructor({port,config_file_name}={})
    {
        if(typeof config_file_name !== "string") 
            throw new Error("config_file_name is not a string")
        this.port = undefined
        this.config = load_setting(join_path(__dirname,config_file_name))
        if(port === undefined) return
        this.port = new SerialPort(port,this.config)
    }
    get available_port()
    {
        return SerialPort.list()
    }
    connect(port)
    {
        console.error(this.port)
        if(typeof this.port === 'undefined')
        {
            return
        }
        this.port = new SerialPort(port,this.config)
    }
}

module.exports = {
    Driver: Driver
}