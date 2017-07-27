#!/usr/bin/env python

import os
import shutil
import glob
import urllib
import zipfile

def remove_if_exists(path):
    """Remove a file or directory if it already exists."""

    if os.path.exists(path):
        shutil.rmtree(path)


def create_dir(path):
    """Create a directory if it does not yet exist.

    If the path exists, but is not a directory, the corresponding item is
    removed, and a directory is created instead.
    """

    if os.path.exists(path) and not os.path.isdir(path):
        shutil.rmtree(path)

    if not os.path.exists(path):
        os.makedirs(path)


def download_file(url, target_dir):
    """Download a file by URL into requested directory.

    Arguments
        url        -- URL of the file to download
        target_dir -- directory to download into

    Returns path to downloaded file on disk.
    """

    create_dir(target_dir)

    file_name = os.path.basename(url)
    target_file = os.path.join(target_dir, file_name)
    urllib.urlretrieve(url, target_file)

    return target_file


def copy_by_pattern(pattern, target_dir):
    """Copy files and directories to another directory.

    Arguments:
        pattern    -- Wildcard for items to be copied, as in glob.
        target_dir -- Directory to copy items into.
    """

    if not os.path.exists(target_dir):
        os.makedirs(target_dir)

    for source_item in glob.glob(pattern):
        item_name = os.path.basename(source_item)
        target_item = os.path.join(target_dir, item_name)

        if os.path.exists(target_item):
            print 'WARNING: item already exists: {0}'.format(target_item)

        if os.path.isdir(source_item):
            shutil.copytree(source_item, target_item)
        else:
            shutil.copy(source_item, target_item)


class ItemSet(object):
    """Items to be copied from a third-party library."""

    def __init__(self, src_wildcard, target_dir):
        self.src_wildcard = src_wildcard
        self.target_dir = target_dir


class Library(object):
    """Third-party library required by the project."""

    def __init__(self, name, url, item_sets):
        self.name = name
        self.url = url
        self.item_sets = item_sets

    def unpack(self, temp_dir, target_dir):
        """Prepare library for usage in the project."""

        print 'downloading library: {0}'.format(self.name)

        archive = download_file(self.url, temp_dir)

        zip_file = zipfile.ZipFile(archive, 'r')
        zip_file.extractall(temp_dir)

        for item_set in self.item_sets:
            wildcard = '{0}/{1}'.format(temp_dir, item_set.src_wildcard)
            item_target_dir = os.path.join(target_dir, item_set.target_dir)
            copy_by_pattern(wildcard, item_target_dir)


LIBRARIES = [
    Library(
        'SDL',
        'https://libsdl.org/release/SDL2-devel-2.0.5-VC.zip',
        [
            ItemSet('SDL2-2.0.5/include/*', 'include'),
            ItemSet('SDL2-2.0.5/lib/x86/*.lib', 'lib/windows-x86-debug'),
            ItemSet('SDL2-2.0.5/lib/x86/*.lib', 'lib/windows-x86-release'),
            ItemSet('SDL2-2.0.5/lib/x64/*.lib', 'lib/windows-x64-debug'),
            ItemSet('SDL2-2.0.5/lib/x64/*.lib', 'lib/windows-x64-release'),
            ItemSet('SDL2-2.0.5/lib/x86/*.dll', 'bin/windows-x86-debug'),
            ItemSet('SDL2-2.0.5/lib/x86/*.dll', 'bin/windows-x86-release'),
            ItemSet('SDL2-2.0.5/lib/x64/*.dll', 'bin/windows-x64-debug'),
            ItemSet('SDL2-2.0.5/lib/x64/*.dll', 'bin/windows-x64-release'),
        ]),
    Library(
        'SDL_image',
        'https://libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.1-VC.zip',
        [
            ItemSet('SDL2_image-2.0.1/include/*', 'include'),
            ItemSet('SDL2_image-2.0.1/lib/x86/*.lib', 'lib/windows-x86-debug'),
            ItemSet('SDL2_image-2.0.1/lib/x86/*.lib', 'lib/windows-x86-release'),
            ItemSet('SDL2_image-2.0.1/lib/x64/*.lib', 'lib/windows-x64-debug'),
            ItemSet('SDL2_image-2.0.1/lib/x64/*.lib', 'lib/windows-x64-release'),
            ItemSet('SDL2_image-2.0.1/lib/x86/*.dll', 'bin/windows-x86-debug'),
            ItemSet('SDL2_image-2.0.1/lib/x86/*.dll', 'bin/windows-x86-release'),
            ItemSet('SDL2_image-2.0.1/lib/x64/*.dll', 'bin/windows-x64-debug'),
            ItemSet('SDL2_image-2.0.1/lib/x64/*.dll', 'bin/windows-x64-release'),
        ]),
    Library(
        'SDL_ttf',
        'https://libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.14-VC.zip',
        [
            ItemSet('SDL2_ttf-2.0.14/include/*', 'include'),
            ItemSet('SDL2_ttf-2.0.14/lib/x86/*.lib', 'lib/windows-x86-debug'),
            ItemSet('SDL2_ttf-2.0.14/lib/x86/*.lib', 'lib/windows-x86-release'),
            ItemSet('SDL2_ttf-2.0.14/lib/x64/*.lib', 'lib/windows-x64-debug'),
            ItemSet('SDL2_ttf-2.0.14/lib/x64/*.lib', 'lib/windows-x64-release'),
            ItemSet('SDL2_ttf-2.0.14/lib/x86/*.dll', 'bin/windows-x86-debug'),
            ItemSet('SDL2_ttf-2.0.14/lib/x86/*.dll', 'bin/windows-x86-release'),
            ItemSet('SDL2_ttf-2.0.14/lib/x64/*.dll', 'bin/windows-x64-debug'),
            ItemSet('SDL2_ttf-2.0.14/lib/x64/*.dll', 'bin/windows-x64-release'),
        ]),
]

def main():
    script_dir = os.path.dirname(os.path.realpath(__file__))
    temp_dir = os.path.join(script_dir, 'tmp')
    target_dir = os.path.join(script_dir, '3p')

    remove_if_exists(target_dir)

    for library in LIBRARIES:
        library.unpack(temp_dir, target_dir)

if __name__ == '__main__':
    main()
