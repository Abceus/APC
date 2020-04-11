import os
import shutil


def linear_compare(fname, fname_other):
    if os.path.getsize(fname) != os.path.getsize(fname_other):
        return False
    
    with open(fname, "rb") as f:
        with open(fname_other, "rb") as f_other:
            for chunk in iter(lambda: f.read(4096), b""):
                chunk_other = f_other.read(4096)
                if chunk != chunk_other:
                    return False
    return True

def copy_changed_directory(path, dest):
    if os.path.exists(path) and os.path.isdir(path):
        files = os.listdir(path)
        for file_ in files:
            source_file_path = os.path.join(path, file_)
            dest_file_path = os.path.join(dest, file_)
            if os.path.isdir(source_file_path):
                copy_changed_directory(source_file_path, dest_file_path)
            elif os.path.isfile(source_file_path):
                need_copy = not (os.path.exists(dest_file_path) and linear_compare(dest_file_path, source_file_path))
                if need_copy:
                    if not os.path.exists(dest):
                        os.makedirs(dest)
                    shutil.copyfile(source_file_path, dest_file_path)
                    print("Copy " + source_file_path + " to " + dest)
                else:
                    print(source_file_path + " skipped")