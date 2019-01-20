import React from 'react';
import './header-content.css';

const headerContent = () => {
    return (<div className="App">
        <header className="App-header">
            <div className="header-welcome">Welcome <b>Guest!</b></div>
            <div>
                <b>OS-WASABI:</b><br/>
                Open Source Warning and Alert Systems A and B Implementation
            </div>
        </header>
    </div>);
};

export default headerContent;