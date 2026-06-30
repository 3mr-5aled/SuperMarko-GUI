# Merge search-bar to master Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Safely merge all updates and features from the `search-bar` branch into `master` while ensuring no regressions and a clean build.

**Architecture:** Create a temporary local integration branch `merge-search-bar-to-master` from `master`, merge `search-bar` into it, resolve any merge conflicts, compile and build the solution, run manual/functional checks, and finally fast-forward/merge the changes into the local and remote `master` branch.

**Tech Stack:** Git, MSBuild/Visual Studio C++ compiler, Windows Forms.

---

### Task 1: Check out and update master
**Files:**
- Modify: None (git checkout/pull operations)

- [ ] **Step 1: Check out master branch**
Run: `git checkout master`
Expected: Switched to branch 'master'

- [ ] **Step 2: Pull latest changes from remote master**
Run: `git pull origin master`
Expected: Pull complete and branch is up to date

- [ ] **Step 3: Run baseline check by compiling master branch**
Run: `& "C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe" SuperMarko-GUI.sln -p:Configuration=Debug -p:Platform=x64 -t:Build`
Expected: Build succeeded with 0 Error(s).

### Task 2: Create a local merge branch and run merge
**Files:**
- Modify: None (git checkout/branch operations)

- [ ] **Step 1: Create and switch to local integration branch**
Run: `git checkout -b merge-search-bar-to-master`
Expected: Switched to a new branch 'merge-search-bar-to-master'

- [ ] **Step 2: Merge search-bar branch into integration branch**
Run: `git merge search-bar`
Expected: Git outputs results of merge. If conflicts exist, files like `MyForm.h`, `DataModels.h`, or `README.md` will be flagged.

### Task 3: Resolve conflicts and commit
**Files:**
- Modify: Any files with conflicts (e.g. `MyForm.h`, `DataModels.h`, `README.md`)

- [ ] **Step 1: Verify files with merge conflicts**
Run: `git status`
Expected: Lists conflicting files under "Unmerged paths" (or "nothing to commit" if merged cleanly).

- [ ] **Step 2: Inspect and resolve merge conflicts**
For any conflicting files listed in Step 1, open them, resolve conflicts by choosing the correct block, and delete conflict markers (`<<<<<<<`, `=======`, `>>>>>>>`).
Expected: Conflict markers removed, code valid.

- [ ] **Step 3: Stage resolved files**
Run: `git add .`
Expected: Files staged for commit.

- [ ] **Step 4: Commit the merge**
Run: `git commit -m "Merge branch 'search-bar' into master"`
Expected: Commit complete.

### Task 4: Verify integration build
**Files:**
- Modify: None (compilation check)

- [ ] **Step 1: Build the solution on integration branch**
Run: `& "C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe" SuperMarko-GUI.sln -p:Configuration=Debug -p:Platform=x64 -t:Build`
Expected: Build succeeded with 0 Error(s).

### Task 5: Fast-forward/merge to local master branch and push
**Files:**
- Modify: None (git checkout/merge operations)

- [ ] **Step 1: Checkout master branch**
Run: `git checkout master`
Expected: Switched to branch 'master'

- [ ] **Step 2: Merge the integration branch into master**
Run: `git merge merge-search-bar-to-master`
Expected: Fast-forward merge completes successfully.

- [ ] **Step 3: Push changes to remote master**
Run: `git push origin master`
Expected: Remote master updated.

- [ ] **Step 4: Delete temporary integration branch**
Run: `git branch -d merge-search-bar-to-master`
Expected: Deleted branch merge-search-bar-to-master.
