#ifndef FILEIO_H_
#define FILEIO_H_

#define MAXDIRNUM 1024
#define MAXPATH   256

class File{
	public:
		File(const char * filename, const char * path);
		~File();
		
	public:
		std::string Filename;
		std::string Path;
		std::string FullPath;
		int GetFileSize();
};

class FileListItem{
	public:
		FileListItem(File* file);
		~FileListItem();
		
	public:
		File* FilePnt;
		FileListItem* Next;
		FileListItem* Previous;
};

class FileList{
	public:
		FileList();
		~FileList();
		void Add(File* file);
		void Remove(File* file);
		void ReadFilesToFileList(string path);
		void ReadFilesToFileList(string path,string extension);
		void ReadDirsToFileList(string path);
		void ReadToFileList(string path);
		void Reset();
		File* GetNextFile();
		File* GetPreviousFile();
		File* GetCurrentFile();
		File* GetFile(int filenumber); 
		int FileCount();
		
	private:
		void RegisterFileListItem(FileListItem* item);
		void Read(string path, bool dirs, bool extensionMask, string extension);
		void ReadDirs(string path);
		
	private:
		FileListItem* _start;
		FileListItem* _end;
		FileListItem* _current;
		int _fileCount;
};

#endif 
