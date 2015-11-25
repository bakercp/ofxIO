#!/bin/bash
set -ev
echo "Publishing docs."

if [[ $TRAVIS_PULL_REQUEST == "false" ]]; then

# Generate doxygen files.
cd docs/;
doxygen Doxyfile;

# Publish html.
git config --global user.name "Travis-CI"
git config --global user.email ${GIT_EMAIL}

# rm -rf gh-pages || exit 0;
git clone --branch=gh-pages https://github.com/${TRAVIS_REPO_SLUG}.git gh-pages

# Copy the tagfile.
cp tagfile.xml gh-pages/

# Copy the documentation html.
cp -R html/* gh-pages/
(
	cd gh-pages;
	git add --all .;
	git commit -m "Travis ofxAddon documentation generation.";
	git remote set-url origin "https://${GH_TOKEN}@github.com/${TRAVIS_REPO_SLUG}.git"
#	git push -fq origin gh-pages > /dev/null 2>&1
    git push -fq origin gh-pages
)

cd ..

else
    echo "Skipping document generation since this is a pull request.";
fi
