# Run the container for tests

From your project folder on Windows, run:
```bash
docker run --rm -it -v "$(pwd):/home/vagrant/compilers" cffs/compilers /bin/sh
su vagrant
cd ~/compilers
ls
```
# Test regex: https://regex101.com/

# Tar to submit work: `cp -r part1 vsopcompiler; tar cfJ vsopcompiler.tar.xz vsopcompiler`
