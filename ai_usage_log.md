# AI Usage Log

**Platform:** Codex desktop  
**Model:** GPT-6

---

## Interaction 1

### User

See the files pointed at in your current directory within Lab 04 folder.&#x20;



Follow all instructions as asked within these. The final result is a github repo link. Utilize the KU cycles skill for testing.



Assignment description:&#x20;



"**Lab 4 - C programming**

**Objective:&#x20;**&#x47;et familiar with C programming and practice Git again. During the C programming, you will practice the basic file operations, if-statements, loops, function calls, and output format control.

**What to** **turn** **in**: Please provide a URL to your GitHub repository. *Make sure the repository is public. Otherwise, the TAs won't be able to grade it.&#xA0;*

***Grading:***

- The first programming problem. Name it "task1.c" [40 points]
- The second programming problem. Name it "task2.c" [40 points]
- The valid Makefile to compile both programs and remove both executables: "all" and "clean" [20 points]
- Demo
- For every programming problem, we will use some test cases to test the robustness and functionality. You especially need to make sure the program can handle invalid inputs. For example, in the first problem, the program should be able to identify that the negative score is invalid."

### Assistant Summary

Read the assignment PDF, AI logging instructions, and Gen-AI guide using the PDF skill, and read the KU Cycle C Test skill. Identified the conflicting Hot interval in the PDF and selected 25 to below 35 degrees Celsius to avoid overlapping Comfortable. Generated task1.c to enumerate football scoring combinations, task2.c to convert temperatures and provide categories and advisories, and a Makefile with all, clean, and test targets. Added validation for invalid numeric input, negative scores, long lines, invalid scales, nonfinite temperatures, below-absolute-zero temperatures, and EOF. Created a Python black-box test suite, an expected-output fixture extracted from the PDF, a README with build and demo instructions, and this usage log. The local build completed without warnings and all 10 test methods passed. An initial sandboxed GitHub authentication check failed; the network-enabled check confirmed valid authentication and that the intended Lab 4 repository did not already exist. Initialized and committed the local Git repository. Used the KU Cycle skill to copy it into a unique temporary directory on cycle1.eecs.ku.edu, verify tracked files and history, build with GCC 11.4.0, run all 10 test methods and representative demos, and check make clean and clean Git status. All checks passed without compiler warnings; tar emitted warnings about unsupported macOS extended metadata during transfer. Removed the temporary directory through a cleanup trap and verified its absence in a separate SSH check. Created and pushed the public repository at https://github.com/MatthewBisbee/eecs-348-lab-4. Recorded the Cycle results in the README, confirmed GitHub reports PUBLIC visibility, and verified a fresh public clone on Cycle 1: the build and all tests passed, make clean removed both executables, Git stayed clean, and a separate SSH check confirmed remote cleanup. The README includes commands and topics for the student’s required live demo; no live TA demo was performed.

---

## Interaction 2

### User

Review what was needed in the repo for final submission. AI usage log stays along with what else is deemed needed. I don't believe the instructions or assignment description is necessary, but the makefile, c, whatever else asked for is.

Also what is the best pipeline for demo? Run commands on my local machine for testing or commands to first ssh into cycle from my mac and then run these? What are these commands in any case

### Assistant Summary

Reviewed the submission requirements and repository file list. Kept task1.c, task2.c, Makefile, and ai_usage_log.md as required deliverables, along with optional README, .gitignore, and regression tests. Removed the three instructor handouts from Git tracking while preserving their local copies, and added ignore rules for those handouts and macOS debug artifacts. Updated the README with submission guidance and commands for both local practice and an interactive Cycle demo from a fresh public clone in a temporary directory. Recommended Cycle for the live demo because it matches the environment already tested, with local runs for practice. Explained sample inputs, invalid-input demonstrations, running make test, and cleanup. No program source or test logic changed in this cleanup.

---

## Interaction 3

### User

See the last lab, as it had the same identical issue as what I'm about to describe, but was resolved properly:

my first interaction to you was "Carefully review all instructions and prompts detailed in the files in this Lab 03 directory. You'll find that the final result of this once complete should be a link to a new github public repo..." but instead you detail things like "User

\<recommended\_plugins> Here is a list of plugins that are available but not installed.

- Airtable (airtable\@openai-curated-remote)
- Alpaca (alpaca\@openai-curated-remote)
- Apollo.io (apollo\@openai-curated-remote)..." as first interaction. and things like "Prefer the Mac's system default browser for browser-based authentication and ordinary web workflows whenever the task and available tooling all..." after that

you can make a footnote at the end about this stuff if you think worth retaining at all, but it is not genuinely my interactions with you like what you're calling interaction 2 and 3 are. this is underlying agentic context from previous interactions that should be considered, in effect, part of you the model itself at this point, not instructions relevant to this chat

### Assistant Summary

Reviewed the corrected Lab 03 log and applied the same distinction to Lab 04: automatically supplied plugin listings, environment metadata, and inherited browser preferences are agent context, not student conversation. Removed the incorrectly numbered context entry, renumbered the actual Lab 04 requests so the original assignment request is Interaction 1, and added this correction verbatim as Interaction 3. Omitted the unnecessary context rather than retaining it as a footnote.
