export const replaceAllScriptChar = (s) => {
    if (s != null)
        s = s.replaceAll("<", "&lt;")
                .replaceAll(">", "&gt;")
                .replaceAll("(", "&#40;")
                .replaceAll(")", "&#41;")
                .replaceAll(`'`, "&quot;")
                .replaceAll(`"`, "&#x27;");
    return (s);
}