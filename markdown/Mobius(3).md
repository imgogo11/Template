### Mobius(3)

$$
\sum_{x=1}^n \sum_{x=1}^m d(xy) \\
=\sum_{x=1}^n \sum_{y=1}^m \sum_{d|xy} 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
=\sum_{x=1}^n \sum_{y=1}^m \sum_{i|x} \sum_{j|y} [(i,j)=1] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
=\sum_{i=1}^n \sum_{j=1}^m \lfloor \frac{n}{i} \rfloor \lfloor \frac{m}{j} \rfloor [(i,j)=1] ~~(交换前两个\sum和后两个\sum枚举顺序) \\
=\sum_{x=1}^n \sum_{y=1}^m \sum_{d|(i,j)} \mu(d) \lfloor \frac{n}{i} \rfloor \lfloor \frac{m}{j} \rfloor ~~(\epsilon=I*\mu) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
=\sum_{d=1}^n \mu(d) \sum_{d|i} \sum_{d|j} \lfloor \frac{n}{i} \rfloor \lfloor \frac{m}{j} \rfloor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
=\sum_{d=1}^n \mu(d) \sum_{i=1}^{\frac{n}{d}} \lfloor \frac{n}{di} \rfloor \sum_{j=1} ^{\frac{m}{d}} \lfloor \frac{m}{dj} \rfloor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
$$

上式首先预数论分块预处理出$\sum_{i=1}^x \lfloor \frac{x}{i} \rfloor~~~O(n\sqrt{n})$     然后整个式子也就可以通过数论分块求得
$$
\sum_{i=1}^n \sum_{j=1}^m \gcd(a_i,b_j) \\
=\sum_{i=1}^n \sum_{j=1}^m \sum_{d|gcd(a_i,b_j)} \varphi(d) \\
=\sum_{d=1}^n \varphi(d) \sum_{i=1}^n [d|a_i] \sum_{j=1}^m [d|b_j] \\
$$
分别预处理出$a$数组和$b$数组中，对于每个$d$倍数的个数，然后枚举$d$即可算
$$
\sum_{i=1}^n \sum_{j=1}^m [\gcd(i,j)=p] ~~~~~~ (p \in Primes) \\
=\sum_{x \in Primes} \sum_{d=1}^{\lfloor \frac{n}{x} \rfloor} \mu(d) \lfloor \frac{n}{xd} \rfloor \lfloor \frac{m}{xd} \rfloor ~~~~~~~~(上略为常规步骤)\\
=\sum_{T=1}^n \lfloor \frac{n}{T} \rfloor \lfloor \frac{m}{T} \rfloor \sum_{x|T,x \in Primes} \mu(\frac{T}{x}) \\
$$
$\sum_{x|T,x \in Primes} \mu(\frac{T}{x})$该部分可以预处理，所以整个式子只需要预处理后分块即可