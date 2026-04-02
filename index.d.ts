/**
 * If `proxy` is a {@link Proxy} object, return its target, otherwise return
 * `undefined`
 */
export declare function inspectProxy<T>(proxy: T): T | undefined

export declare function inspectPromise<T>(promise: Promise<T>):
    | ['pending', undefined]
    | ['resolved', T]
    | ['rejected', unknown]
