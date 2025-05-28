# Get_next_line 📖

[![42 School](https://img.shields.io/badge/42-School-blue)](https://42firenze.it/)
[![GitHub license](https://img.shields.io/github/license/Nazar963/42_get_next_line)](https://github.com/Nazar963/42_get_next_line/blob/master/LICENSE)
[![Build Status](https://img.shields.io/github/actions/workflow/status/Nazar963/42_get_next_line/.github/workflows/build.yml?branch=main)](https://github.com/Nazar963/42_get_next_line/.github/workflows/build.yml)
[![Bonus](https://img.shields.io/badge/Bonus-Complete-brightgreen)](https://github.com/Nazar963/42_get_next_line)

A robust line-reading function that handles file descriptors, supports multiple files simultaneously, and manages edge cases efficiently.

## Table of Contents 📖
- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Build_libraries](#build_libraries)
- [Testing](#testing)
- [Acknowledgments](#acknowledgments)
- [License](#license)

## Description
This 42 School project implements a function that reads a line ending with a newline (`'\n'`) from a file descriptor. The bonus version adds support for:
- Multiple file descriptors management
- Single static variable usage
- No BUFFER_SIZE limitation

**Key Features**:
- Efficient memory management
- Error handling for file operations
- Compliance with various BUFFER_SIZE values
- Full bonus implementation with multiple FD support

## Features

### Core Functionality 🔧
- Reads one line at a time from file/text
- Handles different BUFFER_SIZE values (1 to INT_MAX)
- Manages multiple file descriptors simultaneously (bonus)
- Properly returns -1 on read errors
- Uses single static variable (bonus compliant)

### Edge Case Handling 🛡️
- Empty files
- Files ending without newline
- Alternating reads between multiple FDs
- Very long lines (larger than BUFFER_SIZE)
- Binary files with null characters

## Installation 

### Requirements
- GCC (GNU Compiler Collection)
- GNU Make

### Compilation
1. Clone the repository:
   ```bash
   git clone https://github.com/Nazar963/42_get_next_line.git
   cd 42_get_next_line
   ```
2. Build the project:
   ```bash
   chmod +x build_libraries.sh
   ./build_libraries.sh
   ```
3. Archive libraries (`libgnl.a`, `libgnl_bonus.a`) will be created

## Usage

Include the header in your project:
```c
#include "42_get_next_line/get_next_line.h"
```
Or for the bonus part:
```c
#include "42_get_next_line/get_next_line_bonus.h"
```

Compile with:
```bash
gcc -Wall -Wextra -Werror your_project.c -L42_get_next_line -lgnl -I. -o output
```
Or for the bonus part:
```bash
gcc -Wall -Wextra -Werror your_project.c -L42_get_next_line -lgnl_bonus -I. -o output
```

### Example
```c
#include "42_get_next_line/get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*loco;
	fd = 0;
	fd = open("test.txt", O_RDONLY);
	loco = get_next_line(fd);
	printf("%s", loco);
	free(loco);
	loco = get_next_line(fd);
	printf("%s", loco);
	free(loco);
	loco = get_next_line(fd);
	printf("%s", loco);
	free(loco);
	loco = get_next_line(fd);
	printf("%s", loco);
	free(loco);
	loco = get_next_line(fd);
	printf("%s", loco);
	free(loco);
	return (0);
}
```
Or for the bonus part:
```c
#include "42_get_next_line/get_next_line_bonus.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main( void)
{
	int		fd1;
	int		fd2;
	char	*line;

	fd1 = open("test1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd1 < 0)
	{
		printf("Error creating test1.txt\n");
		return (1);
	}
	write(fd1, "This is line 1 from file 1\n", 27);
	write(fd1, "This is line 2 from file 1\n", 27);
	write(fd1, "This is line 3 from file 1\n", 27);
	close(fd1);

	fd2 = open("test2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 < 0)
	{
		printf("Error creating test2.txt\n");
		return (1);
	}
	write(fd2, "This is line 1 from file 2\n", 27);
	write(fd2, "This is line 2 from file 2\n", 27);
	close(fd2);
	
	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	
	if (fd1 < 0 || fd2 < 0)
	{
		printf("Error opening test files\n");
		return (1);
	}

	line = get_next_line(fd1);
	printf("File 1, Line 1: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("File 2, Line 1: %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("File 1, Line 2: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("File 2, Line 2: %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("File 1, Line 3: %s", line);
	free(line);

	line = get_next_line(fd2);
	if (line)
	{
		printf("File 2, Line 3: %s", line);
		free(line);
	}
	else
		printf("File 2, Line 3: (NULL - End of file)\n");
	
	line = get_next_line(-1);
	if (line == NULL)
		printf("Invalid FD test: Correctly returned NULL\n");
	else
	{
		printf("Invalid FD test: Error - did not return NULL\n");
		free(line);
	}

	close(fd1);
	close(fd2);
	return (0);
}
```

## Build_libraries
Made with AI specifically, Claude 3.7 Sonnet attached to the MCP servers, which are:
- FileSystem
- GitHub
- GitLab
- Memory

As you can see, it simply compiles, archives, and deletes the object files.

## Testing
Validated with:
- [Tripouille/gnlTester](https://github.com/Tripouille/gnlTester)
- [mrjvs/42Cursus_GNL_Tests](https://github.com/mrjvs/42Cursus_GNL_Tests)

## Acknowledgments
- 42 School project guidelines
- Peer code reviews
- Open source testing frameworks
- System programming concepts from UNIX documentation

## 🤝 Contributing
Feel free to submit issues or pull requests if you have suggestions for improving the test suite or adding more test cases.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 📧 Contact
For questions or feedback, please open an issue in the repository.

---

🚀 **Star this repository if you find it useful!**  
[![GitHub stars](https://img.shields.io/github/stars/Nazar963/42_get_next_line?style=social)](https://github.com/Nazar963/42_get_next_line/stargazers)

[![42 School](https://img.shields.io/badge/42-profile-blue)](https://profile-v3.intra.42.fr/users/naal-jen)
[![GitHub Profile](https://img.shields.io/badge/GitHub-Nazar963-lightgrey)](https://github.com/Nazar963)

---

Good luck with your Get_next_line project at 42! 🚀
