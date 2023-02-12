'use strict';

subsets(3);

function subsets(n) {
    const backtrack = function (subs, start, n) {
        if (is_solution(subs, start, n)) {
            process_solution(subs);
        } else {
            let candidates = construct_candidates();

            for (let i = 0; i < candidates.length; i++) {
                subs[start] = candidates[i];
                backtrack(subs, start+1, n);
            }
        }
    }

    let s = new Array(n)
    backtrack(s, 0, n);
}

function construct_candidates() {
    return [
        true,
        false,
    ];
}

function process_solution(subs) {
    let solution = [];

    for (let i = 0; i < subs.length; i++) {
        if (subs[i] === true) {
            solution.push(i+1);
        }
    }

    console.log(solution);
}

function is_solution(subs, i, n) {
    return i === n;
}
