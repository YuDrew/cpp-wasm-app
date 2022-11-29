# Proposal for CIS1900
Author: Andrew Yu ([YuDrew](https://github.com/YuDrew))

## Summary
I'm interested in creating a web application that can automate specific, repeated tasks I've seen in previous jobs, from labeling emails/websites to linking tables. However, I don't want to pay for significant web-hosted computing. I'm seeking to use WASM to create a web application powered by C++ that can perform these computations in the browser.

The idea here is that I can leverage the lightweight power of C++ to perform larger data manipulations completely client-side.

**Potential Processes (60%):**
- Taking a list of emails from the User, scraping web data about the websites (lazily, and then ideally uploading scraped data to an external database so that we don't do this so much...), and then clustering those emails using the raw text data from the website. This would be a C++ implementation of a previous project I've done but haven't put in production, [Strategic Subscriber Segmentation](https://github.com/YuDrew/strategic-subscriber-segmentation). It would utilize WASM (for the app), Apache Arrow (for dataframe processing), Tensorflow (for client-side clustering), and potentially I would need to use databases like Firebase or Amazon DynamoDB and Python for web scraping. 
- Taking a list of different tables from the Affinity CRM (Customer Relationship Management) tool and merging them quickly and efficiently. First, I'd like to replicate what I built for [Affinity Insights](https://affinity-insights.herokuapp.com/) tool. It's built in Flask and hosted in Heroku (which is shutting down hosting today...), and I think WASM and C++ will be powerful enough to create a web application that can process salesperson-scale CRM data completely client-side. This would utilize WASM and Apache Arrow primarily, though there is room for additional work using TensorFlow to continue clustering entries for business client classifications (i.e. infer company type).

## Libraries/Frameworks
- [Web Assembly (WASM)](https://webassembly.org/) Framework in order to easily translate C++ (and many other ) into web applications.
- [Apache Arrow](https://arrow.apache.org/docs/cpp/getting_started.html) in order to perform database / dataframe computation in a low-memory environment (like a web browser).
- [TensorFlow](https://www.tensorflow.org/api_docs/cc) Library useful for different numerical statistical / ML algorithms. Would be used to augment labeling!

## Class Hierarchy / Structure - Implementing User Hierachy (20%):
- The data is primarily managed via Apache Arrow, and this is a bit of an abstraction away from OOP
- Abstract Class User: Users own workflows. 
    - Individual Subclass: Users who may belong to one or many organizations. Will need a login.
    - Guest Subclass: No organization affiliation or login.
    - Organization Subclass: Have their own login, and affiliated individuals can also access.
- Workflows Class: The functions I implement are the workflows for now. A potential extension is to let the Users build their own workflows.

## Stitch Together C++/JS/Databases (20%):
Need to stitch it all together, and that will take a lot of Googling / debugging.

## Appendix: Examples of Other WASM C++ Projects
- [CV Sudoku Solver](https://madewithwebassembly.com/showcase/wasm-sudoku-solver/)
- Other Examples from [MadeWithWebAssembly](https://madewithwebassembly.com/)