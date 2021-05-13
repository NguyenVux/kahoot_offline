const {Driver} = require("./driver")

let d = new Driver({config_file_name:"driver_config.json"})
console.log(d.config)


d.connect()