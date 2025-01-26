import { ErrorPage } from "./page.mjs";

export const safe_fetch = async (...param) => {
    const response = await fetch(...param);

    if (response.ok)
        return response;

    ErrorPage.renderErrorPage(response.status);
}