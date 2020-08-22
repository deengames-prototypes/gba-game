#!/bin/python
import sys
import os
import subprocess
import shutil

RAW2GBA = "raw2gba.exe" if sys.platform == "win32" else "raw2gba"
RAW2GBA = os.path.join(os.getcwd(), "tools", RAW2GBA)
AUDIO_DIR = os.path.join(os.getcwd(), 'audio')
OUTPUT_DIR = os.path.join(os.getcwd(), 'source', 'audio')


def convert_audio(audio_dir, output_dir):
    for item in os.listdir(audio_dir):
        item_path = os.path.join(audio_dir, item)

        if os.path.isdir(item_path):
            output_subdir = os.path.join(output_dir, item)
            os.mkdir(output_subdir)
            convert_audio(item_path, output_subdir)

        elif os.path.isfile(item_path) and item.endswith(".wav"):
            subprocess.call([RAW2GBA, item], cwd=audio_dir)

            filename = str(item.split('.')[0])
            header_file = os.path.join(audio_dir, filename + '.h')
            destination_file = os.path.join(output_dir, filename + '.h')

            shutil.move(header_file, destination_file)


def main():
    if not os.path.exists(AUDIO_DIR):
        os.mkdir(AUDIO_DIR)

    if os.path.exists(OUTPUT_DIR):
        shutil.rmtree(OUTPUT_DIR)
    os.mkdir(OUTPUT_DIR)

    convert_audio(AUDIO_DIR, OUTPUT_DIR)


if __name__ == '__main__':
    main()
