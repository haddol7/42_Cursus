export const clientId = "u-s4t2ud-402050bcc80fd44b22dd906bb1bf62221445ecf3d54505cccac61564a53428a2";

export class FTOauth {
    static isAlreadyOauth () {
        if (window.location.href === "http://localhost:5500/42-ascension/web-front/")
            return false;
        return true;
    }

    static getFtOauthCodeFromUrl () {
        const codePos = window.location.href.indexOf("?code=") + 6;
        const pos = window.location.href.substring(codePos);
        return pos;
    }
}