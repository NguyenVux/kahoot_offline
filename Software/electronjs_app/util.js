const fs = require("fs");

function file_extension(file_name)
{
    return file_name.split(".").pop()
}


function load_json(file_name)
{
    let data = fs.readFileSync(file_name);
    return JSON.parse(data.toString())
}


function load_config(config_file_name)
{
    let extension = file_extension(config_file_name)
    try {
        if(extension === "json")
            return load_json(config_file_name)
    } catch (error) {
        if(error.code === "ENOENT")
            console.log("File not found")
        return
    }
}

module.exports.load_setting = load_config