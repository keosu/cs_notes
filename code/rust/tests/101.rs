pub fn longest_common_subsequence(a: &str, b: &str) -> String {
    let a: Vec<_> = a.chars().collect();
    let b: Vec<_> = b.chars().collect();
    let (na, nb) = (a.len(), b.len());

    // res[i][j] is the length of the LCS between a[0..i-1] and b[0..j-1]
    let mut res = vec![vec![0; nb + 1]; na + 1];

    for (i, ci) in a.iter().enumerate() {
        for (j, cj) in b.iter().enumerate() {
            res[i + 1][j + 1] = if ci == cj {
                res[i][j] + 1
            } else {
                res[i][j + 1].max(res[i + 1][j])
            }
        }
    }

    // reconstitute the solution string from the lengths
    let mut result: Vec<char> = Vec::new();
    let (mut i, mut j) = (na, nb);
    while i > 0 && j > 0 {
        if a[i - 1] == b[j - 1] {
            result.push(a[i - 1]);
            i -= 1;
            j -= 1;
        } else if res[i - 1][j] > res[i][j - 1] {
            i -= 1;
        } else {
            j -= 1;
        }
    }

    result.reverse();
    result.iter().collect()
}

pub fn reverse(text: &str) -> String {
    text.chars().rev().collect()
}

mod test { 
    use super::*;

    #[test]
    fn test_simple() {
        assert_eq!(reverse("racecar"), "racecar");
        assert_eq!(reverse("step on no pets"), "step on no pets");
    }

    fn abc(ss: &String) {

        println!("==== len:   {}",  ss);
    }
    #[test]
    fn test_sentence() {
        let mut a = "abc".to_string();
        a += "fds";
        // let b = a.len();
        // let c = std::mem.move(b);
        abc(&a);
        let d = a+ "d";
        println!("==== len:   {}",  d);
    }
}