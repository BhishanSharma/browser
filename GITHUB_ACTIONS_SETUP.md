# Setting Up Automatic Builds with GitHub Actions

This guide will help you set up automatic Windows and Linux builds for your browser project.

## Prerequisites

- GitHub account
- Your project pushed to GitHub

## Setup Steps

### 1. Create the Workflow File

Create the directory structure and workflow file:

```bash
mkdir -p .github/workflows
```

Copy the provided `build.yml` file to `.github/workflows/build.yml`

### 2. Commit and Push

```bash
git add .github/workflows/build.yml
git commit -m "Add GitHub Actions workflow for cross-platform builds"
git push origin main
```

### 3. Check Build Status

1. Go to your repository on GitHub
2. Click on the **"Actions"** tab
3. You should see the workflow running

## What Happens Automatically

### On Every Push or Pull Request:
- ✅ Linux build is compiled and tested
- ✅ Windows build is compiled with full GTK4 support
- ✅ Build artifacts are saved (available for 90 days)
- ✅ You can download executables from the Actions tab

### On Release Creation:
- ✅ Both Linux and Windows binaries are automatically attached
- ✅ Archives are created: `browser-linux-x64.tar.gz` and `browser-windows-x64.zip`

## Creating a Release

To trigger a release with downloadable binaries:

### Via GitHub Web Interface:

1. Go to your repository
2. Click **"Releases"** → **"Create a new release"**
3. Choose a tag version (e.g., `v1.0.0`)
4. Fill in release title and description
5. Click **"Publish release"**
6. Wait a few minutes - binaries will be attached automatically!

### Via Command Line:

```bash
# Create and push a tag
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin v1.0.0

# Then create release on GitHub from that tag
```

## Downloading Built Artifacts

### From Actions Tab (for any commit):

1. Go to **Actions** tab
2. Click on the workflow run
3. Scroll down to **Artifacts** section
4. Download `browser-linux-x64` or `browser-windows-x64`

### From Releases Page (for releases):

1. Go to **Releases** tab
2. Download the `.tar.gz` (Linux) or `.zip` (Windows) file

## Troubleshooting

### Build Fails
- Check the Actions logs for errors
- Most common issues:
  - Missing source files
  - Syntax errors in code
  - Missing dependencies (should be auto-installed)

### No Artifacts
- Make sure the build succeeds
- Check that the artifact upload step runs

### Windows Build Issues
- MSYS2 automatically installs all needed packages
- GTK4 and WebKitGTK are included in the build
- DLLs are automatically copied

## Customization

### Change Build Settings

Edit `.github/workflows/build.yml`:

```yaml
# Add custom compiler flags
run: |
  g++ -std=c++20 -Wall -Wextra -O3 -DCUSTOM_FLAG \
    src/main.cpp src/browser_window.cpp src/browser_tab.cpp \
    $(pkg-config --cflags --libs gtk4 webkitgtk-6.0) \
    -o build/browser
```

### Add More Platforms

Add a new job to `build.yml`:

```yaml
build-macos:
  runs-on: macos-latest
  steps:
    - name: Checkout code
      uses: actions/checkout@v4
    
    - name: Install dependencies
      run: brew install gtk4 webkitgtk
    
    - name: Build
      run: |
        mkdir -p build
        g++ -std=c++20 -O2 \
          src/main.cpp src/browser_window.cpp src/browser_tab.cpp \
          $(pkg-config --cflags --libs gtk4 webkitgtk-6.0) \
          -o build/browser
```

## Best Practices

1. **Always test locally first** with `./build.sh` before pushing
2. **Use semantic versioning** for releases (v1.0.0, v1.1.0, etc.)
3. **Write clear commit messages** - they appear in the Actions log
4. **Check Actions tab** after each push to verify builds succeed
5. **Add release notes** when creating releases

## Costs

- ✅ **GitHub Actions is FREE** for public repositories
- ✅ 2,000 minutes/month for private repositories (free tier)
- ✅ This project typically uses ~5 minutes per build

## Benefits Over Local Cross-Compilation

| Local Build | GitHub Actions |
|-------------|----------------|
| Complex setup (MXE, Docker) | Zero setup |
| 30-60 min first build | Always fast (~5 min) |
| 5GB disk space | No local storage used |
| Manual process | Fully automated |
| Single platform | Multi-platform |
| Need Windows PC | Build Windows from Linux |

## Additional Resources

- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [Workflow Syntax](https://docs.github.com/en/actions/reference/workflow-syntax-for-github-actions)
- [MSYS2 Setup Action](https://github.com/msys2/setup-msys2)

---

**Questions?** Open an issue on the repository!