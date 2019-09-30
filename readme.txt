This is version 27.0.0.0 of a set of C++11 interfaces for the NAG Library,
supplied as a series of header files.

In order to make use of this product you will need a copy of Mark 27.0 of the
NAG Library installed on your system.

Currently only interfaces for a small subset of routines from the NAG Library are
available in this form. These interfaces are automatically generated, and their
primary purpose is to elicit feedback on their design prior to rolling the
process out across the whole library.

A more comprehensive set of documentation is available from the NAG website:
https://www.nag.com/numeric/nl/nagdoc_27cpp/cpphtml/frontmatter/manconts.html

Assuming that you have installed the C++ interfaces into the directory called
[NAGCPP_INSTALL_DIR] then you should have four subdirectories:

[NAGCPP_INSTALL_DIR]/include
  Contains the C++ wrappers and all required utility headers.

[NAGCPP_INSTALL_DIR]/examples
  Contains a sample of examples calling the interfaces.

[NAGCPP_INSTALL_DIR]/tests
  Contains a series of unit tests that have been used to test the supplied
  wrappers.

[NAGCPP_INSTALL_DIR]/scripts
  Contains a number of Linux scripts for compiling and running the examples
  and unit tests. These scripts can also be run from WSL or cygwin. Prior to
  running any of these scripts you should ensure that your environment is set
  up correctly by, for example, running either envvars.bat, nagvars.sh or
  nagvars.csh, supplied with the NAG Library. Which is supplied / required
  depends on whether you are on Windows or Linux and, if on Linux, which shell
  you are using.


When using the C++ interfaces supplied with this readme you will need to add the
directory [NAGCPP_INSTALL_DIR]/include to the list of directories your compiler
searches for header files in addition to using any compiler flags usually
required by the NAG Library (as specified in the Users' Notes supplied with your
version of the library and also available from the NAG website at
https://www.nag.co.uk/content/nag-library-mark-27).
