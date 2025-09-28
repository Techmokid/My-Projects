import os

# === Set your paths here ===
SRC = r"E:/"                           # failing disk (source)
DST = r"Z:/Random SD card backup"      # NAS destination root
# ===========================

def mirror_directories(src: str, dst: str) -> None:
    src = os.path.abspath(src)
    dst = os.path.abspath(dst)

    if not os.path.isdir(src):
        raise SystemExit(f"Source is not a directory or not accessible: {src}")

    # Make sure destination root exists
    os.makedirs(dst, exist_ok=True)

    created = 0
    skipped = 0

    for dirpath, dirnames, _filenames in os.walk(src):
        # Relative path from SRC to this directory
        rel = os.path.relpath(dirpath, src)
        # For the root of SRC, rel == "." — map that to the DST root
        if rel == ".":
            target_dir = dst
        else:
            target_dir = os.path.join(dst, rel)

        try:
            if not os.path.exists(target_dir):
                os.makedirs(target_dir, exist_ok=True)
                print(f"[CREATE] {target_dir}")
                created += 1
            else:
                # Already there — no action
                # print(f"[SKIP]   {target_dir}")
                skipped += 1
        except OSError as e:
            print(f"[ERROR]  {target_dir} -> {e}")

    print(f"\nDone. Created: {created}, already existed: {skipped}")

if __name__ == "__main__":
    mirror_directories(SRC, DST)
