#vogsphere
kinit emsimang@42.FR
git add .
git commit -m "automated push"; git push

# privte repo
cd ../computor1
cp -rfv ../emsimang/* .
git add .
git commit -m "automated push"; git push