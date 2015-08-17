import fnmatch

def fnmatchs(path_,matchs_):
    for m in matchs_:
        if fnmatch.fnmatch(path_,m):
            return True

    return False
