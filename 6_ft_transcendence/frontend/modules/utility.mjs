import { ErrorPage } from "./page/error.mjs"

export const safe_fetch = async (...param) => {
    const response = await fetch(...param);

    if (response.ok)
        return response;

    ErrorPage.render(response.status);
}