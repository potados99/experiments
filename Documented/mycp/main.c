#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

void usage(const char * msg);
void error(const char * msg);
void copy(int source_fd, int dest_fd);
void extract_filename(const char * full_path, char * out_filename);

int main(int argc, char * argv[]) {

	if (argc == 1) {
		// no commandline args!
		usage("No source files.");
	}
	else if (argc == 2) {
		usage("No dest file.");
	}

	char * last_argument = argv[argc - 1];

	mode_t default_dir_mode = S_IRWXU | S_IRUSR | S_IXUSR | S_IRGRP | S_IXGRP; /* 755 */
	mode_t default_file_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

	// Copy multiple files to dorectory?
	if (argc > 3) {
		/**
		 * This means there are more than or equal to two source files.
		   So the DEST must be a directory.
		 */

		char * dest_dir = last_argument;
		int dest_dir_fd = mkdir(dest_dir, default_dir_mode);

		int each_source_fd;
		char each_file_name[128] = {0, };

		int each_dest_fd;

		for (int i = 1; i < argc - 1; ++i) {
			// interate source files.

			extract_filename(argv[i], each_file_name);

			each_source_fd = open(argv[i], O_RDONLY);
			if (errno) printf("Open source error: %s\n", strerror(errno));

			char dir_buf[256] = {0, };
			sprintf(dir_buf, "%s/%s", dest_dir, each_file_name);

//			each_dest_fd = openat(dest_dir_fd, each_file_name, O_RDWR | O_CREAT, default_file_mode);
//			each_dest_fd = openat(dest_dir_fd, argv[i], O_RDWR | O_CREAT, default_file_mode);
#ifdef DEBUG
			printf("file to open: %s\n", dir_buf);
#endif
			each_dest_fd = open(dir_buf, O_RDWR | O_CREAT, default_file_mode);
			if (errno) printf("Open dest error: %s\n", strerror(errno));

			copy(each_source_fd, each_dest_fd);

			close(each_source_fd);
			close(each_dest_fd);
		}

		close(dest_dir_fd);

	}
	else {
		/**
		 * Single source, single destination.
		 */
		char * source_path = argv[1];
		char * dest_path = last_argument;

		int source_fd = open(source_path, O_RDONLY);
		int dest_fd = open(dest_path, O_RDWR | O_CREAT, default_file_mode);

		copy(source_fd, dest_fd);

		close(source_fd);
		close(dest_fd);
	}

        return 0;

}

void usage(const char * msg) {
	puts(msg);

	puts("Usage:\n");
	puts("\t./mycp SOURCE DEST\n");
	puts("\t./mycp SOURCE... DIRECTORY\n");

	exit(127);
}


void error(const char * msg) {
	puts(msg);

	exit(127);
}

void copy(int source_fd, int dest_fd) {
	int read_bytes;
	char buf[1024] = {0, };

	while( (read_bytes = read(source_fd, buf, sizeof(buf))) ) {
		int wrote_bytes;
		if ( (wrote_bytes = write(dest_fd, buf, read_bytes)) <= 0 ) {
			printf("Wrote: %d\n", wrote_bytes);
			printf("Error info: %s\n", strerror(errno));
			error("Failed to write.");
		}
	}
}

void extract_filename(const char * full_path, char * out_filename) {
	char * last_slash = strrchr(full_path, '/');

	sprintf(out_filename, (last_slash == NULL) ? full_path : last_slash + 1);
}
