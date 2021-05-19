const {app} = require('electron')
const {Driver} = require('./driver')


let driver = new Driver({config_file_name:"driver_config.json"});
driver.on("data",console.warn)
driver.connect("COM5").then(()=>{
    console.log("connected")
    driver.write("COM5")
}).catch(console.log)