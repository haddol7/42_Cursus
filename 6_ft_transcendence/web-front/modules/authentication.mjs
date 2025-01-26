import { safe_fetch } from "./utility.mjs";
import { PageManager } from "./page.mjs";

export const clientId = "u-s4t2ud-402050bcc80fd44b22dd906bb1bf62221445ecf3d54505cccac61564a53428a2";

const accessTokenString="accessToken=";
const refreshTokenString="refreshToken=";
export class FTOauth {

    static isAlreadyOauth () {
        if (window.location.href === "http://localhost:5500/42-ascension/web-front/")
            return false;
        return true;
    }

    static getFtOauthCodeFromUrl () {
        const codePos = window.location.href.indexOf("?code=");
        const code = window.location.href.substring(codePos);
        return code;
    }

    static removeCodeFromUrl () {
        const url = new URL(window.location);
        url.searchParams.delete("code");
        return (url.href);
    }

    static sendFTOauthCodeToServer = async () => {
        const code = FTOauth.getFtOauthCodeFromUrl();
        const response = safe_fetch("http://localhost:8200/auth/42/code" + code);
        if (response === null)
            throw (new Error("Wrong Code"));
        
        response.then(async res => {
                const json = await res.json();
                FTOauth.setNewJWTTokenOnCookie(json.access_token, json.refresh_token);
                console.log(json);
                console.log(json.access_token);
                console.log(json.refresh_token);
            });
    }

    static getJWTTokenFromCookie () {
        const tokens = {};
        document.cookie.split(";").forEach(value => {
            let property = value.trim();
            if (property.startsWith(accessTokenString))
                tokens.accessToken = property.substring(accessTokenString.length);
            if (property.startsWith(refreshTokenString))
                tokens.refreshToken = property.substring(refreshTokenString.length);
        });

        if (tokens?.accessToken === undefined || tokens?.refreshToken === undefined)
            return null;

        return tokens;
    }

    static setNewJWTTokenOnCookie (access_token, refresh_token) {
        // if (document.cookie.indexOf(refreshTokenString) !== -1)
        // {
        //     const spliceStart = document.cookie.indexOf(accessTokenString);
        //     const spliceEnd = document.cookie.indexOf(";", document.cookie.indexOf(refreshTokenString)) + 1;
        //     document.cookie = document.cookie.substring(0, spliceStart) + document.cookie.substring(spliceEnd);
        // }
        document.cookie = `${accessTokenString}${access_token};`
        document.cookie = `${refreshTokenString}${refresh_token};`;
    }

    static clearCookie () {
        document.cookie = accessTokenString + '; expires=Thu, 01 Jan 1970 00:00:01 GMT;';
        document.cookie = refreshTokenString + '; expires=Thu, 01 Jan 1970 00:00:01 GMT;';
    }
}

export class JWT {
}

export const logout = () => {
    FTOauth.clearCookie();
    if (PageManager.currentpageStatus.page === PageManager.pageStatus.login.page)
        history.go();
}