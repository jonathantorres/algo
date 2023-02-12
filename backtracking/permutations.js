'use strict';

permutations(3);

function permutations(n) {
    const backtrack = function (perms, start, n) {
        if (is_solution(perms, start, n)) {
            process_solution(perms);
        } else {
            let candidates = construct_candidates(perms, start, n);

            for (let i = 0; i < candidates.length; i++) {
                perms[start] = candidates[i];
                backtrack(perms, start+1, n);
            }
        }
    }

    let s = new Array(n)
    backtrack(s, 0, n);
}

function construct_candidates(perms, k, n) {
    let in_perm = new Array(n);
    let c = [];

    for (let i = 0; i < n; i++) {
        in_perm[i] = false;
    }

    for (let i = 0; i < k; i++) {
        in_perm[perms[i]] = true;
    }

    for (let i = 0; i < n; i++) {
        if (!in_perm[i]) {
            c.push(i);
        }
    }

    return c;
}

function process_solution(perms) {
    let solution = [];

    for (let i = 0; i < perms.length; i++) {
        solution.push(perms[i]+1);
    }

    console.log(solution);
}

function is_solution(perms, k, n) {
    return k === n;
}
