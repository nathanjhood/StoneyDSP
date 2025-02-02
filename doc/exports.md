- ### When and Why to Use `-DSTONEYDSP_EXPORTS`:

	#### Purpose:

	- The `-DSTONEYDSP_EXPORTS` definition is used to specify that symbols (functions, classes, variables) are being exported from a dynamic library (DLL) rather than imported. This distinction is essential for Windows DLLs because the way symbols are handled differs between exporting and importing.

	#### When to Use:

	- ##### Building the Library:

	When you are compiling the source code of the StoneyDSP library itself, you should define `-DSTONEYDSP_EXPORTS`. This ensures that symbols are marked for export.

	- ##### Using the Library:

	When another project is consuming or using the StoneyDSP library (e.g., linking against the DLL), `-DSTONEYDSP_EXPORTS` should NOT be defined. This ensures that symbols are correctly imported.

	#### Example:

	- ##### Building the Library:

	```sh
	g++ -DSTONEYDSP_EXPORTS -o libstoneydsp.so myLibrary.cpp
	```

	- ##### Using the Library:

	```sh
	g++ -o myApplication main.cpp -lstoneydsp
	```

	This approach helps in maintaining clear boundaries between *exporting* and *importing* symbols, ensuring the correct behavior during linking and execution.
