const fs = require("fs");

function file_extension(file_name) {
  return file_name.split(".").pop();
}

const loader = {
  ini: (file_name) => {
    return undefined;
  },
  json: (file_name) => {
    let data = fs.readFileSync(file_name);
    return JSON.parse(data);
  },
};
function load_json(file_name) {
  return JSON.parse(data.toString());
}

function load_ini(file_name) {
  let data = fs.readFileSync(file_name);
  console.log();
}

function load_config(config_file_path) {
  let extension = file_extension(config_file_path);
  try {
    return loader[extension](config_file_path);
  } catch (error) {
    if (error.code === "ENOENT") console.log("File not found");
    return;
  }
}

module.exports = { 
    load_setting: load_config
};
