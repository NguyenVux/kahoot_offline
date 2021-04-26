const SerialPort = require('serialport')
const Delimiter = require('@serialport/parser-delimiter')

const Event = require('events')
const config = require("./util").load_setting("driver_config.json")





if(config === undefined) 
    process.exit(-1)
const port = SerialPort(config.port,{baudRate: config.baudRate})
const parser = port.pipe(new Delimiter({ delimiter: config.delimiter }))



function data_parser(data)
{
    let data_object = {
        mac_addr: `${data[0]}:${data[1]}:${data[2]}:${data[3]}:${data[4]}:${data[5]}`
    }
    return data_object
}



dataEvent = new Event()
parser.on("data",(data)=>
{
    dataEvent.emit("data",data_parser(data))
})

module.exports = dataEvent