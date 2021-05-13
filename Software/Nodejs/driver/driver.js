const SerialPort = require('serialport')
const Delimiter = require('@serialport/parser-delimiter')
const {Transformer} = require('stream')
const Event = require('events')
const {join: join_path} = require('path')
const {load_setting,isArrayOfType } = require('../common')

const bufferable = new Set(["string","buffer"])


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

class Driver extends Event{
    constructor({port,config_file_name}={})
    {
        super()
        if(typeof config_file_name !== "string") 
            throw new Error("config_file_name is not a string")
        this.port = undefined
        this.config = load_setting(join_path(__dirname,config_file_name))
        if(port === undefined) return
        this.port = new SerialPort(port,this.config)
        this.parser = this.port.pipe(new Delimiter(this.config))
    }
    get available_port()
    {
        return SerialPort.list()
    }
    connect(port)
    {
        if(port === undefined)
        {
            return
        }
        this.port = new SerialPort(port,this.config)
        this.parser = this.port.pipe(new Delimiter(this.config))
        this.parser.on("data",data=>{
            this.emit("data",Driver.#data_parser(data))
        })
    }
    write_serial(data)
    {
        if( !bufferable.has(typeof data) && !isArrayOfType(data,"number") ) return
        if(this.port === undefined) return
        this.port.write(data)
    }
    set on_data(callback){
        if(typeof callback !=="function") throw new Error(`callback is not a function\r\n${typeof callback}`);
        this.on('data', callback)
    }
    static #data_parser(data) {
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
}

module.exports = {
    Driver: Driver
}