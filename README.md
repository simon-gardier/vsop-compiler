# Run the container for tests

From your project folder on Windows, run:
```bash
docker run --rm -it -v "$(pwd):/home/vagrant/compilers" cffs/compilers /bin/sh
su vagrant

ls
```
- Test regex: https://regex101.com/
- Tar to submit work: `cd ~/compilers; rm -rf vsopcompiler; rm vsopcompiler.tar.xz; cp -r part2 vsopcompiler; tar cfJ vsopcompiler.tar.xz vsopcompiler`
