const {Driver} = require("./driverv2")

let d =  new Driver()

d.avaiable_port().then((e,err) => {
  console.log(e)
})