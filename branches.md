# branch structure

#### taken from <http://stackoverflow.com/questions/2428722/git-branch-strategy-for-small-dev-team)>

You might benefit from the workflow Scott Chacon describes in Pro Git. In this workflow, you have two branches that always exist, master and develop.

master represents the most stable version of your project and you only ever deploy to production from this branch.

develop contains changes that are in progress and may not necessarily be ready for production.

From the develop branch, you create topic branches to work on individual features and fixes. Once your feature/fix is ready to go, you merge it into develop, at which point you can test how it interacts with other topic branches that your coworkers have merged in. Once develop is in a stable state, merge it into master. It should always be safe to deploy to production from master.

Scott describes these long-running branches as "silos" of code, where code in a less stable branch will eventually "graduate" to one considered more stable after testing and general approval by your team.

Step by step, your workflow under this model might look like this:

You need to fix a bug.
Create a branch called myfix that is based on the develop branch.
Work on the bug in this topic branch until it is fixed.
Merge myfix into develop. Run tests.
You discover your fix conflicts with another topic branch hisfix that your coworker merged into develop while you were working on your fix.
Make more changes in the myfix branch to deal with these conflicts.
Merge myfix into develop and run tests again.
Everything works fine. Merge develop into master.
Deploy to production from master any time, because you know it's stable.
For more details on this workflow, check out the Branching Workflows chapter in Pro Git.


