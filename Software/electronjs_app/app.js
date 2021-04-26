const data = require("./driver")

data.on("data",async (e)=>
{
    console.log((e));
})