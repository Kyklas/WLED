Import('env', 'projenv')

import os

def light_config(source, target, env):
    variant = env["PIOENV"]
    # create string with location and file names based on variant
    config_dir = "{}{}{}".format("configs", os.path.sep, variant)
    if os.path.isdir(config_dir):
        config_bin = "{}{}wled-spiffs.bin".format("$BUILD_DIR", os.path.sep)
        cmd = "mklittlefs  -s 983040 -c {} {}".format(config_dir,config_bin)
        print("Building Light Config")
        env.Execute(cmd)
    else:
        print(f"No Light Config for {variant} @ {config_dir}")

env.AddPostAction("checkprogsize", light_config)
