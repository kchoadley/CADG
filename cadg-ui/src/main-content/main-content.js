import React from 'react';
import './main-content.css';

const mainContent = () => {
    return (<div className="App">
        <header className="App-content">
            <h1>Welcome!</h1>
            <h2>Please sign in:</h2><br/>
            Username: <input/><br/>
            Password: <input type="password"/><br/>
            <button formAction="POST">Login</button>
        </header>
    </div>);
};

export default mainContent;