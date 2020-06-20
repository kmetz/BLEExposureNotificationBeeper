Import("env", "projenv")

"""
Copies all required binaries to /binaries.
"""

platform = env.PioPlatform()

env.AddPostAction(
    "buildprog",
    env.VerboseAction(" ".join([
        "mkdir -p binaries && cp",
        "/".join([platform.get_package_dir("framework-arduinoespressif32"), "tools/sdk/bin/bootloader_dio_40m.bin"]),
        "binaries/"
    ]), "Copying bootloader_dio_40m.bin to ./binaries")
)

env.AddPostAction(
    "buildprog",
    env.VerboseAction(" ".join([
        "mkdir -p binaries && cp",
        "/".join([platform.get_package_dir("framework-arduinoespressif32"), "tools/partitions/boot_app0.bin"]),
        "binaries/"
    ]), "Copying boot_app0.bin to ./binaries")
)

env.AddPostAction(
    "$BUILD_DIR/partitions.bin",
    env.VerboseAction("mkdir -p binaries && cp $BUILD_DIR/partitions.bin binaries/",
                      "Copying partitions.bin to ./binaries")
)
env.AddPostAction(
    "$BUILD_DIR/${PROGNAME}.bin",
    env.VerboseAction("mkdir -p binaries && cp $BUILD_DIR/${PROGNAME}.bin binaries/",
                      "Copying ${PROGNAME}.bin to ./binaries")
)
