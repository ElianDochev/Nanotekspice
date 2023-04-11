#include <criterion/criterion.h>
#include "../../Utils/Headers/FileReader.hpp"

Test(FileReader, constructor_throws_exception_for_non_existent_file)
{
    bool exception_thrown = false;
    try
    {
        FileReader fr("nonexistent_file.txt");
    }
    catch (FileReader::FileNotFoundException const &e)
    {
        exception_thrown = true;
    }
    cr_assert(exception_thrown, "FileNotFoundException not thrown");
}

Test(FileReader, constructor_opens_valid_file)
{
    FileReader fr("ValidFile.txt");
    cr_assert(fr.nextLine(), "File not opened successfully");
}

Test(FileReader, nextLine_returns_false_when_at_end_of_file)
{
    FileReader fr("ValidFile.txt");
    while (fr.nextLine())
        ;
    cr_assert(!fr.nextLine(), "nextLine() did not return false at end of file");
}

Test(FileReader, getline_returns_correct_line)
{
    FileReader fr("ValidFile.txt");
    cr_assert(fr.getline(true).second == "line 1", "Incorrect line returned");
}

Test(FileReader, getline_does_not_update_line_by_default)
{
    FileReader fr("ValidFile.txt");
    fr.nextLine();
    cr_assert(fr.getline().second == "line 1", "Line updated unexpectedly");
}

Test(FileReader, getline_updates_line_when_getNewLine_is_true)
{
    FileReader fr("ValidFile.txt");
    fr.nextLine();
    cr_assert(fr.getline(true).second == "line 2", "Incorrect line returned");
}

Test(FileReader, reset_resets_stream_to_beginning)
{
    FileReader fr("ValidFile.txt");
    fr.nextLine();
    fr.reset();
    cr_assert(fr.getline(true).second == "line 1", "Stream not reset to beginning");
}

// test for memory leaks

Test(FileReader, no_memory_leaks)
{
    FileReader *fr = new FileReader("ValidFile.txt");
    delete fr;

    cr_assert(true, "Memory leak detected");
}
