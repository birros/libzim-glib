#!/usr/bin/env python3

import sys
import gi
gi.require_version('Zim', '4.0')
from gi.repository import Zim
from gi.repository import GLib

def main (argc, argv):
    if argc == 2:
        filename = argv[1]
    else:
        print ("missing zim file argument", file=sys.stderr)
        exit (1)

    try:
        archive = Zim.Archive.new (filename)
    except GLib.Error as e:
        print (e, file=sys.stderr)
        exit (1)

    assert archive.get_all_entry_count () == 7646
    
    try:
        main_entry = archive.get_main_entry ()
    except GLib.Error as e:
        print (e, file=sys.stderr)
        exit (1)

    assert main_entry.get_title () == "Main Page"

if __name__ == "__main__":
    main (len(sys.argv), sys.argv)
