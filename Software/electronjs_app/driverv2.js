const SerialPort = require('serialport')


class Driver {
    constructor() {
        this.port = undefined
    }
    async avaiable_port() {
        return await SerialPort.list();
    }
}


exports.Driver = Driver