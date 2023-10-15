static int main (string[] argv) {
    string filename;
    if (argv.length == 2) {
        filename = argv[1];
    } else {
        error ("missing zim file argument");
    }

    Zim.Archive archive;
    try {
        archive = new Zim.Archive (filename);
    } catch (Error e) {
        error (e.message);
    }

    assert (archive.get_all_entry_count () == 7646);

    Zim.Entry main_entry;
    try {
        main_entry = archive.get_main_entry ();
    } catch (Error err) {
        error (err.message);
    }

    assert (main_entry.get_title () == "Main Page");

    return 0;
}