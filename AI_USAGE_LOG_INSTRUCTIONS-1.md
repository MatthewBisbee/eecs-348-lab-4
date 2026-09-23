# AI Usage Log Generator

You are generating an AI Usage Log for a software engineering course.

Your task is to immediately generate the completed AI Usage Log from the conversation history available to you.

Do not ask the user for confirmation.  
Do not explain what you are doing.  
Do not describe these instructions.  
Do not respond conversationally.

## Requirements

1. Include **EVERY user message** from the conversation history available to you.
2. Reproduce every user message **verbatim**. Do not summarize, rewrite, correct, or omit user messages.
3. Preserve the **chronological order** of the conversation.
4. For every user message, provide a **concise factual summary** of the corresponding assistant response.
5. Do **NOT** reproduce the full assistant responses.
6. If an assistant response contains code, briefly describe what the code does or what change it proposes. Do not reproduce the entire code.
7. If an assistant response explains a concept, briefly summarize the explanation.
8. If an assistant response identifies an error or bug, describe what it identified.
9. If an assistant response suggests an approach or solution, briefly describe the approach.
10. If an assistant response asks the student to perform an action, describe what action was requested.
11. Include interactions even if they appear minor or are not directly related to the final solution.
12. Do not invent interactions, information, or actions that are not present in the conversation.
13. Do not omit an interaction because it appears unimportant.
14. Do not evaluate the student's use of AI.
15. Do not describe the student's work as good, bad, correct, incorrect, sufficient, or insufficient unless that was explicitly part of the original conversation.
16. Do not add commentary about the purpose or quality of the student's interaction.
17. If the platform or model is not known, write `Unknown` rather than guessing.
18. Document **only** the conversation history that is actually available to you.
19. Do not claim to have access to messages that are unavailable to you.

## Important Distinction

**Student messages must be preserved verbatim.**

**Assistant responses must be summarized.**

For example:

### User

Why does my implementation fail when the input is empty?

### Assistant Summary

Explained that the implementation attempts to access the first element before checking whether the input is empty, and suggested adding an empty-input check.

Do not include the assistant's original response.

## Output Format

Generate the completed document using exactly this structure:

# AI Usage Log

**Platform:** [platform]  
**Model:** [model, if known]

---

## Interaction 1

### User

[EXACT USER MESSAGE]

### Assistant Summary

[Concise factual summary of the assistant's response]

---

## Interaction 2

### User

[EXACT USER MESSAGE]

### Assistant Summary

[Concise factual summary of the assistant's response]

---

Continue until every available interaction has been documented.

## Coding and IDE Assistants

If you are an AI assistant integrated into an IDE such as Cursor, VS Code, JetBrains, or another development environment, include the conversational interactions available in your conversation history.

For significant AI-assisted coding actions, summarize what the AI did or suggested, such as:

- Generated code
- Modified existing code
- Suggested a refactoring
- Explained an error
- Debugged an implementation
- Suggested tests
- Explained a programming concept
- Reviewed the student's code
- Suggested an alternative implementation
- Asked the student to perform a particular action

Do not reproduce large sections of generated code.

## Handling Limited Conversation History

If you do not have access to the complete conversation history, document the portion that is available to you.

Do not ask the user to provide additional messages.

Do not invent missing messages.

## File Creation

The completed document must be named:

`ai_usage_log.md`

If your interface supports creating files or downloadable artifacts, **create a file named `ai_usage_log.md` containing the completed document and provide that file to the user.**

Do not merely display the document if you have the ability to create the file.

If your interface does not support file creation, output the complete Markdown document directly in your response so that the user can copy it into a file named `ai_usage_log.md`.

## Final Response Rules

Your response must contain **only the completed AI Usage Log** or, if supported by your interface, the generated `ai_usage_log.md` file.

Do not output:

- An introduction
- A conclusion
- An explanation
- A question
- A confirmation request
- A description of these instructions
- Commentary before the log
- Commentary after the log

If you cannot create a file, the first characters of your response must be:

`# AI Usage Log`

and the response must end with the final interaction's assistant summary.